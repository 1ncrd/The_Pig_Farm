#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QMetaType>
#include "HomeWindow.hpp"
#include "GameMainWindow.hpp"
#include "ArchiveWindow.hpp"
#include "SettingWindow.hpp"
#include "FileManager.hpp"
#include "BgmPlayer.hpp"
#include "TradeRecordWindow.hpp"
#include "SettingWindow.hpp"

int main(int argc, char *argv[])
{
    // Register the custom type into the `MetaType` to transport them across the QThreads.
    qRegisterMetaType<PigSty>("Pig_Sty");
    qRegisterMetaType<PigSty>("Pig_Sty&");
    qRegisterMetaType<Pig::PigInfo>("PigInfo");
    qRegisterMetaType<Pig::PigInfo>("PigInfo&");
    qRegisterMetaType<FileManager::GameData>("GameData");
    qRegisterMetaType<FileManager::GameData>("GameData&");
    qRegisterMetaType<FileManager::GameData>("GameData&");
    qRegisterMetaType<FileManager::PigStyInfo>("PigStyInfo");
    qRegisterMetaType<FileManager::PigStyInfo>("PigStyInfo&");
    qRegisterMetaType<PigSoldAmount>("PigSoldAmount");
    qRegisterMetaType<PigSoldAmount>("PigSoldAmount&");
    QApplication a(argc, argv);

    // Create GameDatas and SalesRecords Folder.
    FileManager::CreateGameDataFolder();
    FileManager::CreateTradeRecordFolder();

    // Create Initial_Window and Game_Main_Window.
    HomeWindow home_window;
    ArchiveWindow archive_window;
    GameMainWindow game_window;
    SettingWindow setting_window;
    home_window.show();

    // Click the "Start Game" button to show the game window.
    // QObject::connect(&home_window, HomeWindow::OnStartButtonClicked, &Game_window, GameMainWindow::StartGame);
    QObject::connect(&home_window, HomeWindow::OnStartButtonClicked, &archive_window, ArchiveWindow::show);
    QObject::connect(&home_window, HomeWindow::OnSettingButtonClicked, &setting_window, SettingWindow::Start);
    QObject::connect(&archive_window, ArchiveWindow::GameStart, &game_window, GameMainWindow::StartGame);
    QObject::connect(&archive_window, ArchiveWindow::Back, &home_window, HomeWindow::show);
    return a.exec();
}
