/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <LibWeb/DOM/HTMLElement.h>
#include <LibWeb/Loader/Resource.h>

namespace Web {

class HTMLLinkElement final
    : public HTMLElement
    , public ResourceClient {
public:
    HTMLLinkElement(Document&, const FlyString& tag_name);
    virtual ~HTMLLinkElement() override;

    virtual void inserted_into(Node&) override;

    String rel() const { return attribute(HTML::AttributeNames::rel); }
    String type() const { return attribute(HTML::AttributeNames::type); }
    String href() const { return attribute(HTML::AttributeNames::href); }

private:
    // ^ResourceClient
    virtual void resource_did_fail() override;
    virtual void resource_did_load() override;

    void load_stylesheet(const URL&);

    RefPtr<StyleSheet> m_style_sheet;
};

template<>
inline bool is<HTMLLinkElement>(const Node& node)
{
    return is<Element>(node) && to<Element>(node).tag_name() == HTML::TagNames::link;
}

}
