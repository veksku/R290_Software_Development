#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsView>
#include <QMessageBox>
#include <QDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "pregovarac.hpp"
#include "displayElement.hpp"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_import_project_triggered();

    void on_import_image_triggered();

    void on_path_button_accepted();

    void on_path_button_rejected();

    void on_cropp_button_clicked();

    void on_scale_button_2_clicked();

    void on_action_help_triggered();

    void on_action_about_triggered();

    void on_action_change_triggered();

    void on_change_button_accepted();

    void on_actionscale_triggered();

    void on_actionCrop_triggered();

    void on_actionMerge_triggered();

    void on_merge_btn_ok_clicked();

    void on_change_button_rejected();

    void on_actionView_triggered();

    void on_actionRemove_triggered();

    void on_save_triggered();

    void on_actionExport_image_triggered();

    void on_actionEnhance_triggered();

    void on_save_as_triggered();

    void on_crop_exit_clicked();

    void on_scale_exit_clicked();

    void on_merge_exit_clicked();

private:

    void load_project();
    QPointF find_position(unsigned id_ulaza, unsigned element_id);
    void show_no_elements_message(const char* str, std::string mode);
    void show_not_found_message(const char* str, std::string ime_fajla);
    void show_id_cannot_be_empty_message(const char* str);
    void show_unable_to_find_element_message(const char* str, int id);

    unsigned m_jedinstveni_maticni_broj_slike;

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *display_window;
    QString path;
    QString fileName = "";
    Pregovarac pregovarac;

    std::map<QString,std::pair<QString, bool>> labelText;
    std::map<unsigned, QString> element_type;
    std::map<unsigned, displayElement*> elementi;
    std::map<unsigned, std::vector<bool>> ulaz_pozicije;
    std::map<std::pair<qreal, qreal>, bool> popunjene_pozicije;

    unsigned change_element = -1;
    qreal element_x = 0;
    qreal element_y = 100;
    bool remove = false;
};
#endif // MAINWINDOW_HPP
