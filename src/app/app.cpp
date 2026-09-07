#include "app/app.hpp"

#include <filesystem>
#include <memory>

#include <QApplication>
#include <QScreen>
#include <QStyleHints>
#include <ixwebsocket/IXNetSystem.h>
#include <qapplication.h>
#include <qnamespace.h>
#include <qsize.h>
#include <qstylehints.h>
#include <stdx/types.hh>

#include "app/backend_bridge.hpp"
#include "app/theme_bridge.hpp"
#include "app/context.hpp"
#include "app/gui.hpp"
#include "core/log.hpp"
#include "esp32/backend.hpp"
#include "esp32/data.hpp"

namespace mbr {

namespace { const std::filesystem::path DEFAULT_JSON_PATH{"MBR_data.json"}; } // namespace

app_t::app_t(i32 argc, char** argv)
    : qt_app_{std::make_unique<QApplication>(argc, argv)},
      context_{std::make_shared<app_context>()} {
    context_->log = context_->logger.get_log_fn();
    ix::initNetSystem();
    context_->backend = std::make_unique<telemetry_backend>(DEFAULT_JSON_PATH, context_->log);
    context_->bridge  = std::make_unique<ui::bridge::backend_bridge>(*context_->backend);
    context_->theme  = std::make_unique<ui::bridge::theme_bridge>();
    gui_              = std::make_unique<gui_t>(context_);
    context_->backend->start();
    set_theme();
    }

app_t::~app_t() { ix::uninitNetSystem(); }

void app_t::run() {
    gui_->showMaximized();
    qt_app_->exec();
}

void app_t::set_theme() {
    Qt::ColorScheme scheme = qApp->styleHints()->colorScheme();
    if (scheme == Qt::ColorScheme::Dark) {
        qApp->setPalette(context_->theme->theme_manager.get_theme(false));
    } else {
        qApp->setPalette(context_->theme->theme_manager.get_theme(true));
    }
}

} // namespace mbr
