/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
 * Copyright (C) 2015 Devin Rousso <dcrousso+webkit@gmail.com>. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

WebInspector.GradientEditor = class GradientEditor extends WebInspector.Object
{
    constructor()
    {
        super();

        this._element = document.createElement("div");
        this._element.classList.add("gradient-editor");

        this._gradient = null;
        this._gradientTypes = {
            "linear-gradient": {
                type: WebInspector.LinearGradient,
                label: WebInspector.UIString("Linear Gradient"),
                repeats: false
            },
            "radial-gradient": {
                type: WebInspector.RadialGradient,
                label: WebInspector.UIString("Radial Gradient"),
                repeats: false
            },
            "repeating-linear-gradient": {
                type: WebInspector.LinearGradient,
                label: WebInspector.UIString("Repeating Linear Gradient"),
                repeats: true
            },
            "repeating-radial-gradient": {
                type: WebInspector.RadialGradient,
                label: WebInspector.UIString("Repeating Radial Gradient"),
                repeats: true
            }
        };
        this._editingColor = false;

        this._gradientTypePicker = this._element.appendChild(document.createElement("select"));
        this._gradientTypePicker.classList.add("gradient-type-select");
        for (let type in this._gradientTypes) {
            let option = this._gradientTypePicker.appendChild(document.createElement("option"));
            option.value = type;
            option.text = this._gradientTypes[type].label;
        }
        this._gradientTypePicker.addEventListener("change", this._gradientTypeChanged.bind(this));

        this._gradientSlider = new WebInspector.GradientSlider(this);
        this._element.appendChild(this._gradientSlider.element);

        this._colorPicker = new WebInspector.ColorPicker;
        this._colorPicker.colorWheel.dimension = 190;
        this._colorPicker.enableColorComponentInputs = false;
        this._colorPicker.addEventListener(WebInspector.ColorPicker.Event.ColorChanged, this._colorPickerColorChanged, this);

        let angleContainerElement = this._element.appendChild(document.createElement("div"));
        angleContainerElement.classList.add("gradient-angle");
        angleContainerElement.append(WebInspector.UIString("Angle"));

        let boundAngleValueChanged = this._angleValueChanged.bind(this);

        this._angleSliderElement = angleContainerElement.appendChild(document.createElement("input"));
        this._angleSliderElement.type = "range";
        this._angleSliderElement.addEventListener("input", boundAngleValueChanged);

        this._angleInputElement = angleContainerElement.appendChild(document.createElement("input"));
        this._angleInputElement.type = "number";
        this._angleInputElement.addEventListener("input", boundAngleValueChanged);

        this._angleUnitsSelectElement = angleContainerElement.appendChild(document.createElement("select"));
        this._angleUnitsSelectElement.addEventListener("change", this._angleUnitsChanged.bind(this));

        const angleUnitsData = [
            {name: WebInspector.LinearGradient.AngleUnits.DEG, min: 0, max: 360, step: 1},
            {name: WebInspector.LinearGradient.AngleUnits.RAD, min: 0, max: 2 * Math.PI, step: 0.01},
            {name: WebInspector.LinearGradient.AngleUnits.GRAD, min: 0, max: 400, step: 1},
            {name: WebInspector.LinearGradient.AngleUnits.TURN, min: 0, max: 1, step: 0.01}
        ];

        this._angleUnitsConfiguration = new Map(angleUnitsData.map(({name, min, max, step}) => {
            let optionElement = this._angleUnitsSelectElement.appendChild(document.createElement("option"));
            optionElement.value = optionElement.textContent = name;

            return [name, {element: optionElement, min, max, step}];
        }));
    }

    get element()
    {
        return this._element;
    }

    set gradient(gradient)
    {
        if (!gradient)
            return;

        const isLinear = gradient instanceof WebInspector.LinearGradient;
        const isRadial = gradient instanceof WebInspector.RadialGradient;
        console.assert(isLinear || isRadial);
        if (!isLinear && !isRadial)
            return;

        this._gradient = gradient;
        this._gradientSlider.stops = this._gradient.stops;
        if (isLinear) {
            this._gradientTypePicker.value = this._gradient.repeats ? "repeating-linear-gradient" : "linear-gradient";

            this._angleUnitsChanged();
        } else
            this._gradientTypePicker.value = this._gradient.repeats ? "repeating-radial-gradient" : "radial-gradient";

        this._updateCSSClassForGradientType();
    }

    get gradient()
    {
        return this._gradient;
    }

    // Protected

    gradientSliderStopsDidChange(gradientSlider)
    {
        this._gradient.stops = gradientSlider.stops;

        this.dispatchEventToListeners(WebInspector.GradientEditor.Event.GradientChanged, {gradient: this._gradient});
    }

    gradientSliderStopWasSelected(gradientSlider, stop)
    {
        const selectedStop = gradientSlider.selectedStop;
        if (selectedStop && !this._editingColor) {
            this._element.appendChild(this._colorPicker.element);
            this._element.classList.add("editing-color");
            this._colorPicker.color = selectedStop.color;
            this._editingColor = true;
        } else if (!selectedStop) {
            this._colorPicker.element.remove();
            this._element.classList.remove("editing-color");
            this._editingColor = false;
        }

        // Ensure the angle input is not focused since, if it were, it'd make a scrollbar appear as we
        // animate the popover's frame to fit its new content.
        this._angleInputElement.blur();

        this.dispatchEventToListeners(WebInspector.GradientEditor.Event.ColorPickerToggled);
        this.dispatchEventToListeners(WebInspector.GradientEditor.Event.GradientChanged, {gradient: this._gradient});
    }

    // Private

    _updateCSSClassForGradientType()
    {
        const isRadial = this._gradient instanceof WebInspector.RadialGradient;
        this._element.classList.toggle("radial-gradient", isRadial);

        this.dispatchEventToListeners(WebInspector.GradientEditor.Event.ColorPickerToggled);
    }

    _gradientTypeChanged(event)
    {
        const descriptor = this._gradientTypes[this._gradientTypePicker.value];
        if (!(this._gradient instanceof descriptor.type)) {
            if (descriptor.type === WebInspector.LinearGradient) {
                this._gradient = new WebInspector.LinearGradient(180, this._gradient.stops);

                this._angleUnitsChanged();
            } else
                this._gradient = new WebInspector.RadialGradient("", this._gradient.stops);

            this._updateCSSClassForGradientType();
        }
        this._gradient.repeats = descriptor.repeats;

        this.dispatchEventToListeners(WebInspector.GradientEditor.Event.GradientChanged, {gradient: this._gradient});
    }

    _colorPickerColorChanged(event)
    {
        this._gradientSlider.selectedStop.color = event.target.color;
        this._gradientSlider.stops = this._gradient.stops;

        this.dispatchEventToListeners(WebInspector.GradientEditor.Event.GradientChanged, {gradient: this._gradient});
    }

    _angleValueChanged(event)
    {
        switch (event.target) {
        case this._angleInputElement:
            this._gradient.angleValue = this._angleSliderElement.value = parseFloat(this._angleInputElement.value) || 0;
            break;
        case this._angleSliderElement:
            this._gradient.angleValue = this._angleInputElement.value = parseFloat(this._angleSliderElement.value) || 0;
            break;
        default:
            WebInspector.reportInternalError("Input event fired for disabled color component input");
            return;
        }

        this.dispatchEventToListeners(WebInspector.GradientEditor.Event.GradientChanged, {gradient: this._gradient});
    }

    _angleUnitsChanged(event)
    {
        let units = this._angleUnitsSelectElement.value;
        let configuration = this._angleUnitsConfiguration.get(units);
        if (!configuration) {
            WebInspector.reportInternalError(`Missing configuration data for selected angle units "${units}"`);
            return;
        }

        this._gradient.angleUnits = units;

        this._angleInputElement.min = this._angleSliderElement.min = configuration.min;
        this._angleInputElement.max = this._angleSliderElement.max = configuration.max;
        this._angleInputElement.step = this._angleSliderElement.step = configuration.step;
        this._angleInputElement.value = this._angleSliderElement.value = this._gradient.angleValue;

        this.dispatchEventToListeners(WebInspector.GradientEditor.Event.GradientChanged, {gradient: this._gradient});
    }
};

WebInspector.GradientEditor.Event = {
    GradientChanged: "gradient-editor-gradient-changed",
    ColorPickerToggled: "gradient-editor-color-picker-toggled"
};
