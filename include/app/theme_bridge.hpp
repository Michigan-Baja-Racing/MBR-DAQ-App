#pragma once

#include <QObject>
#include <qobject.h>
#include <qtmetamacros.h>

#include "assets/style.hpp"

namespace mbr::ui::bridge {

class theme_bridge : public QObject {
    Q_OBJECT
    public:
        explicit theme_bridge(QObject* parent = nullptr) : QObject(parent) {
            theme_manager.initialize_pallets();
        }
        void apply(style::theme_mode mode);

    public:
        style::theme_manager theme_manager;

    signals:
        void theme_changed(bool light);

    private:
        style::theme_mode current_mode = style::theme_mode::SYSTEM;

};

} // namespace mbr::ui::bridge
