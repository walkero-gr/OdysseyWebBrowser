/*
 * Copyright (C) 2018 Apple Inc. All rights reserved.
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

#pragma once

#if ENABLE(LAYOUT_FORMATTING_CONTEXT)

#include "LayoutUnits.h"
#include "RenderStyleConstants.h"
#include <wtf/IsoMalloc.h>

namespace WebCore {

class RenderStyle;

namespace Layout {
class BlockFormattingContext;
class FormattingContext;
class FloatingContext;
class LayoutContext;
}

namespace Display {

class Box {
    WTF_MAKE_ISO_ALLOCATED(Box);
public:
    friend class Layout::BlockFormattingContext;
    friend class Layout::FormattingContext;
    friend class Layout::FloatingContext;
    friend class Layout::LayoutContext;

    Box(const Box&);

    class Rect {
    public:
        Rect() = default;
        Rect(LayoutUnit top, LayoutUnit left, LayoutUnit width, LayoutUnit height);
        
        LayoutUnit top() const;
        LayoutUnit left() const;
        LayoutPoint topLeft() const;

        LayoutUnit bottom() const;
        LayoutUnit right() const;        
        LayoutPoint bottomRight() const;

        LayoutUnit width() const;
        LayoutUnit height() const;
        LayoutSize size() const;

        void setTop(LayoutUnit);
        void setLeft(LayoutUnit);
        void setTopLeft(const LayoutPoint&);
        void setWidth(LayoutUnit);
        void setHeight(LayoutUnit);
        void setSize(const LayoutSize&);

        void shiftLeftTo(LayoutUnit);
        void shiftRightTo(LayoutUnit);
        void shiftTopTo(LayoutUnit);
        void shiftBottomTo(LayoutUnit);

        void moveHorizontally(LayoutUnit);
        void moveVertically(LayoutUnit);

        void expand(LayoutUnit, LayoutUnit);
        bool intersects(const Rect& rect) const { return m_rect.intersects(rect); }

        Rect clone() const;
        operator LayoutRect() const;

    private:
#if !ASSERT_DISABLED
        void invalidateTop() { m_hasValidTop = false; }
        void invalidateLeft() { m_hasValidLeft = false; }
        void invalidateWidth() { m_hasValidWidth = false; }
        void invalidateHeight() { m_hasValidHeight = false; }
        void invalidatePosition();

        bool hasValidPosition() const { return m_hasValidTop && m_hasValidLeft; }
        bool hasValidSize() const { return m_hasValidWidth && m_hasValidHeight; }
        bool hasValidGeometry() const { return hasValidPosition() && hasValidSize(); }
    
        void setHasValidPosition();
        void setHasValidSize();

        bool m_hasValidTop { false };
        bool m_hasValidLeft { false };
        bool m_hasValidWidth { false };
        bool m_hasValidHeight { false };
#endif
        LayoutRect m_rect;
    };

    ~Box();

    LayoutUnit top() const;
    LayoutUnit left() const;
    LayoutUnit bottom() const { return top() + height(); }
    LayoutUnit right() const { return left() + width(); }

    LayoutPoint topLeft() const;
    LayoutPoint bottomRight() const { return { right(), bottom() }; }

    LayoutSize size() const { return { width(), height() }; }
    LayoutUnit width() const { return borderLeft() + paddingLeft().value_or(0) + contentBoxWidth() + paddingRight().value_or(0) + borderRight(); }
    LayoutUnit height() const { return borderTop() + paddingTop().value_or(0) + contentBoxHeight() + paddingBottom().value_or(0) + borderBottom(); }
    Rect rect() const { return { top(), left(), width(), height() }; }
    Rect rectWithMargin() const { return { top() - marginTop(), left() - marginLeft(), marginLeft() + width() + marginRight(), marginTop() + height() + marginBottom() }; }

    LayoutUnit marginTop() const;
    LayoutUnit marginLeft() const;
    LayoutUnit marginBottom() const;
    LayoutUnit marginRight() const;

    LayoutUnit nonCollapsedMarginTop() const;
    LayoutUnit nonCollapsedMarginBottom() const;
    std::optional<LayoutUnit> estimatedMarginTop() const { return m_estimatedMarginTop; }

    LayoutUnit borderTop() const;
    LayoutUnit borderLeft() const;
    LayoutUnit borderBottom() const;
    LayoutUnit borderRight() const;

    std::optional<LayoutUnit> paddingTop() const;
    std::optional<LayoutUnit> paddingLeft() const;
    std::optional<LayoutUnit> paddingBottom() const;
    std::optional<LayoutUnit> paddingRight() const;

    LayoutUnit contentBoxTop() const { return borderTop() + paddingTop().value_or(0); }
    LayoutUnit contentBoxLeft() const { return borderLeft() + paddingLeft().value_or(0); }
    LayoutUnit contentBoxBottom() const { return contentBoxTop() + contentBoxHeight(); }
    LayoutUnit contentBoxRight() const { return contentBoxLeft() + contentBoxWidth(); }
    LayoutUnit contentBoxHeight() const;
    LayoutUnit contentBoxWidth() const;

    Rect marginBox() const;
    Rect nonCollapsedMarginBox() const;

    Rect borderBox() const;
    Rect paddingBox() const;
    Rect contentBox() const;

private:
    Box(const RenderStyle&);

    struct Style {
        Style(const RenderStyle&);

        BoxSizing boxSizing { BoxSizing::ContentBox };
    };

    void setTopLeft(const LayoutPoint&);
    void setTop(LayoutUnit);
    void setLeft(LayoutUnit);
    void moveHorizontally(LayoutUnit offset) { m_topLeft.move(offset, { }); }
    void moveVertically(LayoutUnit offset) { m_topLeft.move({ }, offset); }

    void setContentBoxHeight(LayoutUnit);
    void setContentBoxWidth(LayoutUnit);

    void setHorizontalMargin(Layout::HorizontalEdges);
    void setVerticalMargin(Layout::VerticalEdges);
    void setVerticalNonCollapsedMargin(Layout::VerticalEdges);
    void setEstimatedMarginTop(LayoutUnit marginTop) { m_estimatedMarginTop = marginTop; }

    void setBorder(Layout::Edges);
    void setPadding(std::optional<Layout::Edges>);

#if !ASSERT_DISABLED
    void invalidateMargin();
    void invalidateBorder() { m_hasValidBorder = false; }
    void invalidatePadding() { m_hasValidPadding = false; }

    void setHasValidTop() { m_hasValidTop = true; }
    void setHasValidLeft() { m_hasValidLeft = true; }
    void setHasValidVerticalMargin() { m_hasValidVerticalMargin = true; }
    void setHasValidVerticalNonCollapsedMargin() { m_hasValidVerticalNonCollapsedMargin = true; }
    void setHasValidHorizontalMargin() { m_hasValidHorizontalMargin = true; }

    void setHasValidBorder() { m_hasValidBorder = true; }
    void setHasValidPadding() { m_hasValidPadding = true; }

    void setHasValidContentHeight() { m_hasValidContentHeight = true; }
    void setHasValidContentWidth() { m_hasValidContentWidth = true; }
#endif

    const Style m_style;

    LayoutPoint m_topLeft;
    LayoutUnit m_contentWidth;
    LayoutUnit m_contentHeight;

    Layout::Edges m_margin;
    Layout::VerticalEdges m_verticalNonCollapsedMargin;
    std::optional<LayoutUnit> m_estimatedMarginTop;

    Layout::Edges m_border;
    std::optional<Layout::Edges> m_padding;

#if !ASSERT_DISABLED
    bool m_hasValidTop { false };
    bool m_hasValidLeft { false };
    bool m_hasValidHorizontalMargin { false };
    bool m_hasValidVerticalMargin { false };
    bool m_hasValidVerticalNonCollapsedMargin { false };
    bool m_hasValidBorder { false };
    bool m_hasValidPadding { false };
    bool m_hasValidContentHeight { false };
    bool m_hasValidContentWidth { false };
#endif
};

#if !ASSERT_DISABLED
inline void Box::Rect::invalidatePosition()
{
    invalidateTop();
    invalidateLeft();
}

inline void Box::Rect::setHasValidPosition()
{
    m_hasValidTop = true;
    m_hasValidLeft = true;
}

inline void Box::Rect::setHasValidSize()
{
    m_hasValidWidth = true;
    m_hasValidHeight = true;
}

inline void Box::invalidateMargin()
{
    m_hasValidHorizontalMargin = false;
    m_hasValidVerticalMargin = false;
}
#endif

inline LayoutUnit Box::Rect::top() const
{
    ASSERT(m_hasValidTop);
    return m_rect.y();
}

inline LayoutUnit Box::Rect::left() const
{
    ASSERT(m_hasValidLeft);
    return m_rect.x();
}

inline LayoutUnit Box::Rect::bottom() const
{
    ASSERT(m_hasValidTop && m_hasValidHeight);
    return m_rect.maxY();
}

inline LayoutUnit Box::Rect::right() const
{
    ASSERT(m_hasValidLeft && m_hasValidWidth);
    return m_rect.maxX();
}

inline LayoutPoint Box::Rect::topLeft() const
{
    ASSERT(hasValidPosition());
    return m_rect.minXMinYCorner();
}

inline LayoutPoint Box::Rect::bottomRight() const
{
    ASSERT(hasValidGeometry());
    return m_rect.maxXMaxYCorner();
}

inline LayoutSize Box::Rect::size() const
{
    ASSERT(hasValidSize());
    return m_rect.size();
}

inline LayoutUnit Box::Rect::width() const
{
    ASSERT(m_hasValidWidth);
    return m_rect.width();
}

inline LayoutUnit Box::Rect::height() const
{
    ASSERT(m_hasValidHeight);
    return m_rect.height();
}

inline void Box::Rect::setTopLeft(const LayoutPoint& topLeft)
{
#if !ASSERT_DISABLED
    setHasValidPosition();
#endif
    m_rect.setLocation(topLeft);
}

inline void Box::Rect::setTop(LayoutUnit top)
{
#if !ASSERT_DISABLED
    m_hasValidTop = true;
#endif
    m_rect.setY(top);
}

inline void Box::Rect::setLeft(LayoutUnit left)
{
#if !ASSERT_DISABLED
    m_hasValidLeft = true;
#endif
    m_rect.setX(left);
}

inline void Box::Rect::setWidth(LayoutUnit width)
{
#if !ASSERT_DISABLED
    m_hasValidWidth = true;
#endif
    m_rect.setWidth(width);
}

inline void Box::Rect::setHeight(LayoutUnit height)
{
#if !ASSERT_DISABLED
    m_hasValidHeight = true;
#endif
    m_rect.setHeight(height);
}

inline void Box::Rect::setSize(const LayoutSize& size)
{
#if !ASSERT_DISABLED
    setHasValidSize();
#endif
    m_rect.setSize(size);
}

inline void Box::Rect::shiftLeftTo(LayoutUnit left)
{
    ASSERT(m_hasValidLeft);
    m_rect.shiftXEdgeTo(left);
}

inline void Box::Rect::shiftRightTo(LayoutUnit right)
{
    ASSERT(m_hasValidLeft && m_hasValidWidth);
    m_rect.shiftMaxXEdgeTo(right);
}

inline void Box::Rect::shiftTopTo(LayoutUnit top)
{
    ASSERT(m_hasValidTop);
    m_rect.shiftYEdgeTo(top);
}

inline void Box::Rect::shiftBottomTo(LayoutUnit bottom)
{
    ASSERT(m_hasValidTop && m_hasValidHeight);
    m_rect.shiftMaxYEdgeTo(bottom);
}

inline void Box::Rect::moveHorizontally(LayoutUnit offset)
{
    ASSERT(m_hasValidLeft);
    m_rect.move(offset, { });
}

inline void Box::Rect::moveVertically(LayoutUnit offset)
{
    ASSERT(m_hasValidTop);
    m_rect.move({ }, offset);
}

inline void Box::Rect::expand(LayoutUnit width, LayoutUnit height)
{
    ASSERT(hasValidGeometry());
    m_rect.expand(width, height);
}

inline Box::Rect Box::Rect::clone() const
{
    Rect rect;
#if !ASSERT_DISABLED
    rect.m_hasValidTop = m_hasValidTop;
    rect.m_hasValidLeft = m_hasValidLeft;
    rect.m_hasValidWidth = m_hasValidWidth;
    rect.m_hasValidHeight  = m_hasValidHeight;
#endif 
    rect.m_rect = m_rect;
    return rect;
}

inline Box::Rect::operator LayoutRect() const
{
    ASSERT(hasValidGeometry()); 
    return m_rect;
}

inline LayoutUnit Box::top() const
{
    ASSERT(m_hasValidTop && (m_estimatedMarginTop || m_hasValidVerticalMargin));
    return m_topLeft.y();
}

inline LayoutUnit Box::left() const
{
    ASSERT(m_hasValidLeft && m_hasValidHorizontalMargin);
    return m_topLeft.x();
}

inline LayoutPoint Box::topLeft() const
{
    ASSERT(m_hasValidTop && (m_estimatedMarginTop || m_hasValidVerticalMargin));
    ASSERT(m_hasValidLeft && m_hasValidHorizontalMargin);
    return m_topLeft;
}

inline void Box::setTopLeft(const LayoutPoint& topLeft)
{
#if !ASSERT_DISABLED
    setHasValidTop();
    setHasValidLeft();
#endif
    m_topLeft = topLeft;
}

inline void Box::setTop(LayoutUnit top)
{
#if !ASSERT_DISABLED
    setHasValidTop();
#endif
    m_topLeft.setY(top);
}

inline void Box::setLeft(LayoutUnit left)
{
#if !ASSERT_DISABLED
    setHasValidLeft();
#endif
    m_topLeft.setX(left);
}

inline void Box::setContentBoxHeight(LayoutUnit height)
{ 
#if !ASSERT_DISABLED
    setHasValidContentHeight();
#endif
    m_contentHeight = height;
}

inline void Box::setContentBoxWidth(LayoutUnit width)
{ 
#if !ASSERT_DISABLED
    setHasValidContentWidth();
#endif
    m_contentWidth = width;
}

inline LayoutUnit Box::contentBoxHeight() const
{
    ASSERT(m_hasValidContentHeight);
    return m_contentHeight;
}

inline LayoutUnit Box::contentBoxWidth() const
{
    ASSERT(m_hasValidContentWidth);
    return m_contentWidth;
}

inline void Box::setHorizontalMargin(Layout::HorizontalEdges margin)
{
#if !ASSERT_DISABLED
    setHasValidHorizontalMargin();
#endif
    m_margin.horizontal = margin;
}

inline void Box::setVerticalMargin(Layout::VerticalEdges margin)
{
#if !ASSERT_DISABLED
    setHasValidVerticalMargin();
#endif
    ASSERT(!m_estimatedMarginTop || *m_estimatedMarginTop == margin.top);
    m_margin.vertical = margin;
}

inline void Box::setVerticalNonCollapsedMargin(Layout::VerticalEdges margin)
{
#if !ASSERT_DISABLED
    setHasValidVerticalNonCollapsedMargin();
#endif
    m_verticalNonCollapsedMargin = margin;
}

inline void Box::setBorder(Layout::Edges border)
{
#if !ASSERT_DISABLED
    setHasValidBorder();
#endif
    m_border = border;
}

inline void Box::setPadding(std::optional<Layout::Edges> padding)
{
#if !ASSERT_DISABLED
    setHasValidPadding();
#endif
    m_padding = padding;
}

inline LayoutUnit Box::marginTop() const
{
    ASSERT(m_hasValidVerticalMargin);
    return m_margin.vertical.top;
}

inline LayoutUnit Box::marginLeft() const
{
    ASSERT(m_hasValidHorizontalMargin);
    return m_margin.horizontal.left;
}

inline LayoutUnit Box::marginBottom() const
{
    ASSERT(m_hasValidVerticalMargin);
    return m_margin.vertical.bottom;
}

inline LayoutUnit Box::marginRight() const
{
    ASSERT(m_hasValidHorizontalMargin);
    return m_margin.horizontal.right;
}

inline LayoutUnit Box::nonCollapsedMarginTop() const
{
    ASSERT(m_hasValidVerticalNonCollapsedMargin);
    return m_verticalNonCollapsedMargin.top;
}

inline LayoutUnit Box::nonCollapsedMarginBottom() const
{
    ASSERT(m_hasValidVerticalNonCollapsedMargin);
    return m_verticalNonCollapsedMargin.bottom;
}

inline std::optional<LayoutUnit> Box::paddingTop() const
{
    ASSERT(m_hasValidPadding);
    if (!m_padding)
        return { };
    return m_padding->vertical.top;
}

inline std::optional<LayoutUnit> Box::paddingLeft() const
{
    ASSERT(m_hasValidPadding);
    if (!m_padding)
        return { };
    return m_padding->horizontal.left;
}

inline std::optional<LayoutUnit> Box::paddingBottom() const
{
    ASSERT(m_hasValidPadding);
    if (!m_padding)
        return { };
    return m_padding->vertical.bottom;
}

inline std::optional<LayoutUnit> Box::paddingRight() const
{
    ASSERT(m_hasValidPadding);
    if (!m_padding)
        return { };
    return m_padding->horizontal.right;
}

inline LayoutUnit Box::borderTop() const
{
    ASSERT(m_hasValidBorder);
    return m_border.vertical.top;
}

inline LayoutUnit Box::borderLeft() const
{
    ASSERT(m_hasValidBorder);
    return m_border.horizontal.left;
}

inline LayoutUnit Box::borderBottom() const
{
    ASSERT(m_hasValidBorder);
    return m_border.vertical.bottom;
}

inline LayoutUnit Box::borderRight() const
{
    ASSERT(m_hasValidBorder);
    return m_border.horizontal.right;
}

}
}
#endif
