//
// Copyright (c) 2009 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:	MIT
//


#pragma once


#include "ofColor.h"
#include "ofTrueTypeFont.h"


namespace ofx {
namespace MUI {


enum FontSize
{
	EXTRA_SMALL = 0,
	SMALL = 1,
	MEDIUM = 2,
	LARGE = 3,
	EXTRA_LARGE = 4
};


class TrueTypeFontSettings
{
public:
	TrueTypeFontSettings(const std::string& filename = DEFAULT_FONT,
						 int fontsize = defaultFontSize(FontSize::MEDIUM),
						 bool antiAliased = true,
						 bool fullCharacterSet = true,
						 bool makeContourss = false,
						 float simplifyAmt = 0.3f,
						 int dpi = 0);

	const std::string& filename() const;
	int fontSize() const;
	bool antiAliased() const;
	bool fullCharacterSet() const;
	bool makeContours() const;
	float simplifyAmount() const;
	int dpi() const;

    /// \brief The default font name.
	static const std::string DEFAULT_FONT;

    /// \brief Get the font size in pixels for the given FontSize.
    /// \param size The named FontSize.
    /// \returns the size in pixels.
	static int defaultFontSize(FontSize size = FontSize::MEDIUM);

	static TrueTypeFontSettings defaultFontSettings(FontSize size = FontSize::MEDIUM);

private:
	std::string _filename;
	int _fontsize;
	bool _antiAliased;
	bool _fullCharacterSet;
	bool _makeContours;
	float _simplifyAmt;
	int _dpi;

};


/// \brief A common class for setting shared Widget styles.
class Styles
{
public:
    /// \brief Each Style has a role.
	enum Role
	{
        /// \brief Styles applied to the foreground.
		ROLE_FOREGROUND = 0,
        /// \brief Styles applied to the background.
		ROLE_BACKGROUND,
        /// \brief Styles applied to the accent areas.
		ROLE_ACCENT,
        /// \brief Styles applied to the borders.
		ROLE_BORDER,
        /// \brief Styles applied to the text.
		ROLE_TEXT
	};

    /// \brief Each style can also be applied to an interaction state.
	enum State
	{
        /// \brief The normal target is idle.
		STATE_NORMAL = 0,
        /// \brief The state when a pointer is over the target.
		STATE_OVER,
        /// \brief The state when a target is down.
		STATE_DOWN,
        /// \brief The state when a target is disabled.
		STATE_DISABLED
	};

    /// \brief Create a default styles.
	Styles();

    /// \brief Destroy these styles.
    virtual ~Styles();

    /// \brief Set colors for each role in the Style.
    /// \param foreground The foreground color.
    /// \param background The background color.
    /// \param accent The accent color.
    /// \param border The border color.
    /// \param text The text color.
	void setColors(const ofColor& foreground,
				   const ofColor& background,
				   const ofColor& accent,
				   const ofColor& border,
				   const ofColor& text);

    /// \brief Get the ofColor for a given Role and State.
    /// \param role The Role desired.
    /// \param state The State desired.
    /// \returns an ofColor for the given role and state.
	const ofColor& getColor(Role role, State state) const;

    /// \brief Set the ofColor for a given Role and State.
    /// \param color The color to set.
    /// \param role The Role desired.
    /// \param state The State desired.
    void setColor(const ofColor& color, Role role, State state);

    /// \brief Get the font for a given FontSize.
    /// \param size The font size to get.
    /// \returns a reference to the requested font.
	const ofTrueTypeFont& getFont(FontSize size = FontSize::MEDIUM) const;

    /// \brief Set the font for a given FontSize.
    /// \param size The FontSize for the font.
    /// \param font The cached font to use.
	void setFont(FontSize size, std::shared_ptr<ofTrueTypeFont> font);

protected:
    /// \brief A collection of colors for this Style.
	std::vector<std::vector<ofColor>> _colors;

    /// \brief A font cache for this Style.
	mutable std::vector<std::shared_ptr<ofTrueTypeFont>> _fonts;

};


} } // ofx::MUI
