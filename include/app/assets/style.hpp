#pragma once

#include <QColor>
#include <QString>
#include <QPalette>
#include <qnamespace.h>

#include <ankerl/unordered_dense.h>

#include "colors.hpp"

#include <qpalette.h>
#include <stdx/types.hh>
#include <stdx/utility.hh>

namespace mbr::ui::style {


// QSS Generators
struct button_style_options {
    int     font_size     = 10;
    int     padding_v     = 6;
    int     padding_h     = 12;
    int     border_radius = 4;
    QString align         = "center";
};

QString make_button_style(const button_style_options& opts = {});
QString make_tree_style();
QString make_menubar_style(int font_size_px = 20);
QString make_menu_style(int font_size_px = 20);
QString make_status_dot_style(const QColor& color, int diameter_px = 20);

enum theme_mode {
    DARK,
    LIGHT,
    SYSTEM,
};

class theme_manager {

    public:
        void initialize_pallets();
        QPalette get_theme(bool light);

    private:
        QPalette dark_p;
        QPalette light_p;
        Qt::ColorScheme current_theme;
};


} // namespace mbr::ui::style
