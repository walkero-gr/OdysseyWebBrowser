/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"

#if ENABLE(CONDITION)

#include "JSTestStandaloneEnumeration.h"

#include <JavaScriptCore/JSCInlines.h>
#include <JavaScriptCore/JSString.h>
#include <wtf/NeverDestroyed.h>


namespace WebCore {
using namespace JSC;

String convertEnumerationToString(TestStandaloneEnumeration enumerationValue)
{
    static const NeverDestroyed<String> values[] = {
        MAKE_STATIC_STRING_IMPL("enumValue1"),
        MAKE_STATIC_STRING_IMPL("enumValue2"),
    };
    static_assert(static_cast<size_t>(TestStandaloneEnumeration::EnumValue1) == 0, "TestStandaloneEnumeration::EnumValue1 is not 0 as expected");
    static_assert(static_cast<size_t>(TestStandaloneEnumeration::EnumValue2) == 1, "TestStandaloneEnumeration::EnumValue2 is not 1 as expected");
    ASSERT(static_cast<size_t>(enumerationValue) < WTF_ARRAY_LENGTH(values));
    return values[static_cast<size_t>(enumerationValue)];
}

template<> JSString* convertEnumerationToJS(ExecState& state, TestStandaloneEnumeration enumerationValue)
{
    return jsStringWithCache(&state, convertEnumerationToString(enumerationValue));
}

template<> Optional<TestStandaloneEnumeration> parseEnumeration<TestStandaloneEnumeration>(ExecState& state, JSValue value)
{
    auto stringValue = value.toWTFString(&state);
    if (stringValue == "enumValue1")
        return TestStandaloneEnumeration::EnumValue1;
    if (stringValue == "enumValue2")
        return TestStandaloneEnumeration::EnumValue2;
    return WTF::nullopt;
}

template<> const char* expectedEnumerationValues<TestStandaloneEnumeration>()
{
    return "\"enumValue1\", \"enumValue2\"";
}

} // namespace WebCore

#endif // ENABLE(CONDITION)
