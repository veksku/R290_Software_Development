#include "../inc/mainwindow.hpp"
#include "ui_mainwindow.h"
#include <iostream>
#include <filesystem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , path(QDir::home().path() + "/home")
{
    ui->setupUi(this);
    QWidget::showMaximized();

    ui->path_widget->hide();
    ui->crop_widget->hide();
    ui->scale_widget->hide();
    ui->merge_widget->hide();
    ui->change_widget->hide();



    this->labelText = {{"import_image",std::make_pair("Path to the image", false)},
                       {"import_project",std::make_pair("Path to the project", false)},
                       {"save_project",std::make_pair("Save project to the path", false)},
                       {"save_image",std::make_pair("Save image to the path", false)}
                    };


    scene = new QGraphicsScene(this);
    ui->displayWindow->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/* import */
void MainWindow::on_import_project_triggered()
{
    ui->path_label->setText(labelText["import_project"].first);
    labelText["import_project"].second = true;
    ui->path_widget->show();
}



void MainWindow::on_import_image_triggered()
{

    ui->path_label->setText(labelText["import_image"].first);
    labelText["import_image"].second = true;
    ui->path_widget->show();

}

/* path */
void MainWindow::on_path_button_accepted()
{
    for (auto lT : labelText) {
        if (lT.first == "import_image") {
            if (lT.second.second == true) {
                QString imgPath = ui->path_input->toPlainText();
                ui->path_widget->hide();
                labelText[lT.first].second = false;
                std::string s = imgPath.toStdString();
                if(!std::filesystem::exists(s)){
                    show_not_found_message(__FUNCTION__, s);
                    return;
                }
                unsigned id = change_element;
                if (change_element == -1) {
                    id = pregovarac.createImg(imgPath);
                    // ako je kreiranje slike uspesno (ako slika postoji na toj putanji)
                    ulaz_pozicije[id] = {false, false, false, false};
                    std::string display_text = "Image\n Element id: " + std::to_string(id);

                    element_type[id] = "Image";
                    elementi[id] = new displayElement(QString::fromStdString(display_text), id);
                    // TO DO - dodati odredjivanje pozicije kad se dodaje nova slika (da se ne crtaju sve slike na istoj poziciji)
                    scene->addItem(elementi[id]);
                    if (id != 0) {
                        QPointF new_position = find_position(id-1, id);
                        elementi[id]->moveBy(new_position.x(), new_position.y());
                    }
                }
                else {
                    pregovarac.changeImage(id, imgPath);
                    change_element = -1;
                }
            }
        }
        else if (lT.first == "import_project" && lT.second.second == true) {
            QString projectPath = ui->path_input->toPlainText();
            ui->path_widget->hide();
            labelText[lT.first].second = false;
            std::string s = projectPath.toStdString();
            if(!std::filesystem::exists(s)){
                show_not_found_message(__FUNCTION__, s);
                return;
            }
            pregovarac.loadProject(projectPath);
            load_project();
        }
        else if (lT.first == "save_project" && lT.second.second == true) {
            if(elementi.size() == 0){
                ui->path_widget->hide();
                show_no_elements_message(__FUNCTION__, "save");
                return;
            }
            QString projectPath = ui->path_input->toPlainText();
            ui->path_widget->hide();
            labelText[lT.first].second = false;
            pregovarac.saveProject(projectPath);
        }
        else if (lT.first == "save_image" && lT.second.second == true) {
            QString imgPath = ui->path_input->toPlainText();
            if(elementi.size() == 0){
                ui->path_widget->hide();
                show_no_elements_message(__FUNCTION__, "save");
                return;
            }
            ui->path_widget->hide();
            labelText[lT.first].second = false;
            pregovarac.saveImage(imgPath, (--elementi.end())->first);
        }
    }
}



void MainWindow::on_path_button_rejected()
{
    for (auto lT : labelText) {
        if (lT.second.second == true)
            labelText[lT.first].second = false;
    }
    ui->path_widget->hide();

}

/* view */
void MainWindow::on_actionView_triggered()
{
    bool ok;
    auto id = QInputDialog::getInt(this,"View", "Input element id: ",0,0,2000,1,&ok);
    if(ok){
        if(elementi.size() == 0){
            show_no_elements_message(__FUNCTION__, "view");
            return;
        }

        QLabel *label_pic;
        label_pic = new QLabel();
        label_pic->setAlignment(Qt::AlignCenter);
       // label_pic->setMargin(0);
        label_pic->setGeometry(QRect(1000, 1000, 1000, 1000));
        std::cout << id << std::endl;
        label_pic->setPixmap(QPixmap::fromImage(*pregovarac.showCurrentImg(id)));
        label_pic->show();

    }
}

/* crop */
void MainWindow::on_actionCrop_triggered()
{
     ui->crop_widget->show();
}

void MainWindow::on_cropp_button_clicked()
{
     if(elementi.size() == 0){
         ui->crop_widget->hide();
         show_no_elements_message(__FUNCTION__, "transformacija");
         return;
     }

     unsigned A_x, A_y, B_x, B_y;
     A_x = ui->A_x->toPlainText().toUInt();
     A_y = ui->A_y->toPlainText().toUInt();

     B_x = ui->B_x->toPlainText().toUInt();
     B_y = ui->B_y->toPlainText().toUInt();

     std::string check = ui->crop_input->toPlainText().toStdString();
     if(check  == ""){
         show_id_cannot_be_empty_message(__FUNCTION__);
         return;
     }
     ui->crop_widget->hide();

     unsigned id = change_element;

     if(change_element == -1) {
         unsigned id_ulaza = ui->crop_input->toPlainText().toUInt();
         if (elementi.find(id_ulaza) == elementi.end()) {
             show_unable_to_find_element_message(__FUNCTION__, id_ulaza);
             return;
         }
         id = pregovarac.CropImage(A_x, A_y, B_x, B_y, id_ulaza);
         // ako je crop uspeo
         std::string display_text = "Crop\n Element id: " + std::to_string(id);
         std::cout << display_text << std::endl;
         elementi[id] = new displayElement(QString::fromStdString(display_text), id);
         element_type[id] = "Crop";

         QPointF new_position = find_position(id_ulaza, id);
         elementi[id]->setPos(new_position);
         //elementi[id]->moveBy(new_position.x(), new_position.y());
         scene->addItem(elementi[id]);
         scene->addItem(new Edge(elementi[id_ulaza], elementi[id]));
     }
     else {
         pregovarac.changeCrop(id, A_x, A_y, B_x, B_y);
         change_element = -1;
     }
}

void MainWindow::on_crop_exit_clicked()
{
     ui->crop_widget->hide();
}

/* scale */
void MainWindow::on_actionscale_triggered()
{
     ui->scale_widget->show();
}

void MainWindow::on_scale_button_2_clicked()
{
      //for(unsigned i = 0; i<element_type.size(); i++){}
      if(elementi.size() == 0){
          ui->scale_widget->hide();

          show_no_elements_message(__FUNCTION__, "transformacija");
          return;
      }
      bool odnosIvica = false , premaVecojIvici = false;
      if (ui->odnosIvica_da->isChecked())
        odnosIvica = true;
      if (ui->premaVecojIvici_da->isChecked())
        premaVecojIvici = true;

      unsigned x, y;
      // ovde se mogu ubaciti neke provere da li je ispravno
      x = ui->dimenzija_x->toPlainText().toUInt();
      y = ui->dimenzija_y->toPlainText().toUInt();

      std::string check = ui->scale_input->toPlainText().toStdString();
      if(check  == ""){
          show_id_cannot_be_empty_message(__FUNCTION__);
          return;
      }
      ui->scale_widget->hide();

      unsigned id = change_element;

      if(change_element == -1) {
        unsigned id_ulaza = ui->scale_input->toPlainText().toUInt();
        if (elementi.find(id_ulaza) == elementi.end()) {
            show_unable_to_find_element_message(__FUNCTION__, id_ulaza);
            return;
        }

        id = pregovarac.ScaleImage(odnosIvica, premaVecojIvici, std::make_pair(x,y), id_ulaza);
        // ako je scale uspeo
        std::string display_text = "Scale\n Element id: " + std::to_string(id);
        element_type[id] = "Scale";
        elementi[id] = new displayElement(QString::fromStdString(display_text), id);
        QPointF new_position = find_position(id_ulaza, id);
        elementi[id]->moveBy(new_position.x(), new_position.y());
        scene->addItem(elementi[id]);
        scene->addItem(new Edge(elementi[id_ulaza], elementi[id]));
      }
      else {
        pregovarac.changeScale(change_element,odnosIvica, premaVecojIvici, std::make_pair(x,y));
        change_element = -1;
      }
}


void MainWindow::on_scale_exit_clicked()
{
      ui->scale_widget->hide();
}



/* change */
void MainWindow::on_action_change_triggered()
{
       ui->change_widget->show();
}


void MainWindow::on_change_button_accepted()
{

      std::string check = ui->change_input->toPlainText().toStdString();
      if(check  == ""){
          show_id_cannot_be_empty_message(__FUNCTION__);
          return;
      }
      ui->change_widget->hide();
      change_element = ui->change_input->toPlainText().toUInt();

      if(elementi.find(change_element) == elementi.end()){
          show_unable_to_find_element_message(__FUNCTION__, change_element);
          return;
      }

      if (remove) {
           elementi[change_element]->changeColor(QColor("gray"));
           elementi[change_element]->update();
           pregovarac.removeElement(change_element);
           //scene->removeItem(elementi[change_element]);
           elementi.erase(change_element);
           element_type.erase(change_element);
           change_element = -1;
           remove = false;
      }
      else if (element_type[change_element] == "Image") {
          ui->path_label->setText(labelText["import_image"].first);
          labelText["import_image"].second = true;
          ui->path_widget->show();
      }
      else if (element_type[change_element] == "Crop") {
          ui->crop_widget->show();
      }
      else if (element_type[change_element] == "Scale") {
          ui->scale_widget->show();
      }
      else if (element_type[change_element] == "Merge") {
          ui->merge_widget->show();
      }
}

void MainWindow::on_change_button_rejected()
{
      ui->change_widget->hide();
      remove = false;
}

/* merge */
void MainWindow::on_merge_btn_ok_clicked()
{
      if(elementi.size() == 0){
          ui->merge_widget->hide();
          show_no_elements_message(__FUNCTION__, "transformacija");
          return;
      }

      std::string check1 = ui->merge_first_id->toPlainText().toStdString();
      std::string check2 = ui->merge_second_id->toPlainText().toStdString();
      if(check1  == "" || check2 == ""){
          QMessageBox::warning(this,
                                  tr("Error!"),
                                  tr("Please enter a valid id - neither of the fields can be empty."));
          std::cerr << "MainWindow::on_merge_btn_ok_clicked() kaze: id_ulaza cannot be empty." << std::endl;
          return;
      }

      ui->merge_widget->hide();
      const bool horizontalno = ui->m_horizontally->isChecked();
      const bool obrnutim_redosledon = ui->m_revere_order->isChecked();
      std::string poravnanje = "center";
      if (ui->align_l->isChecked())
        poravnanje = "left";
      else if (ui->align_r->isChecked())
        poravnanje = "right";

      std::string boja_pozadine = ui->combo_box_color->currentText().toStdString();
      unsigned id_provog_ulaza = ui->merge_first_id->toPlainText().toUInt();
      unsigned id_drugog_ulaza = ui->merge_second_id->toPlainText().toUInt();

      unsigned id = change_element;
      Poravnanje por = poravnanje_from_string(poravnanje);
      if (change_element == -1) {
          id = pregovarac.mergeImage(horizontalno, obrnutim_redosledon, por, boja_pozadine, id_provog_ulaza, id_drugog_ulaza);
          std::string display_text = "Merge Image\n Element id: " + std::to_string(id);
          element_type[id] = "Merge";
          elementi[id] = new displayElement(QString::fromStdString(display_text), id);
          QPointF new_position = find_position(id_drugog_ulaza, id);
          elementi[id]->moveBy(new_position.x(), new_position.y());
          scene->addItem(elementi[id]);
          scene->addItem(new Edge(elementi[id_drugog_ulaza], elementi[id]));
      }
      else {
          pregovarac.changeMerge(id, horizontalno, obrnutim_redosledon, por, boja_pozadine);
          change_element = -1;
      }
}

void MainWindow::on_merge_exit_clicked()
{
      ui->merge_widget->hide();
}

void MainWindow::on_actionMerge_triggered()
{
      ui->merge_widget->show();
}


/* remove */
void MainWindow::on_actionRemove_triggered()
{
    ui->change_widget->show();
    remove = true;
}

/* save as */
void MainWindow::on_save_as_triggered()
{
    if(elementi.size() == 0){
        show_no_elements_message(__FUNCTION__, "save");
        return;
    }
    QString initialPath = MainWindow::path + "/untitled";

    fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                            initialPath,
                                            tr("All Files (*)")
                                            );

    if (fileName.isEmpty())
          return;

    pregovarac.saveProject(fileName);
}

/* save */
void MainWindow::on_save_triggered()
{
    ui->path_label->setText(labelText["save_project"].first);
    labelText["save_project"].second = true;
    ui->path_widget->show();
}

/* load */
void MainWindow::load_project()
{
    element_type = pregovarac.getElement_state();
    for (auto &el : element_type) {
        std::string display_text = el.second.toStdString() + " \n Element id: " + std::to_string(el.first);
        elementi[el.first] = new displayElement(QString::fromStdString(display_text), el.first);
        if (el.second.toStdString() == "Image") {
            ulaz_pozicije[el.first] = {false, false, false, false};

        }
        scene->addItem(elementi[el.first]);
    }

    std::map<unsigned, unsigned> ulazi = pregovarac.getUlazi();
    for (auto &ulaz : ulazi) {
        QPointF new_position = find_position(ulaz.second, ulaz.first);
        elementi[ulaz.first]->moveBy(new_position.x(), new_position.y());
        scene->addItem(new Edge(elementi[ulaz.second], elementi[ulaz.first]));
    }
}

QPointF MainWindow::find_position(unsigned int id_ulaza, unsigned int element_id)
{
    // UP
    qreal x_offset = elementi[id_ulaza]->width() + 100;
    qreal y_offset = elementi[id_ulaza]->height() + 100;
    if (ulaz_pozicije[id_ulaza][0] == false && popunjene_pozicije.find(std::make_pair(elementi[id_ulaza]->x(), elementi[id_ulaza]->y() - y_offset)) == popunjene_pozicije.end()) {
        ulaz_pozicije[id_ulaza][0] = true;
        ulaz_pozicije[element_id] = {false, true, false, false};
        popunjene_pozicije[std::make_pair(elementi[id_ulaza]->x(), elementi[id_ulaza]->y() - y_offset)] = true;
        return QPointF(elementi[id_ulaza]->x(), elementi[id_ulaza]->y() - y_offset);
    }
    // RIGHT
    else if (ulaz_pozicije[id_ulaza][1] == false && popunjene_pozicije.find(std::make_pair(elementi[id_ulaza]->x() + x_offset, elementi[id_ulaza]->y())) == popunjene_pozicije.end()) {
        ulaz_pozicije[id_ulaza][1] = true;
        ulaz_pozicije[element_id] = {false, false, false, true};
        popunjene_pozicije[std::make_pair(elementi[id_ulaza]->x() + x_offset, elementi[id_ulaza]->y())] = true;
        return QPointF(elementi[id_ulaza]->x()  + x_offset, elementi[id_ulaza]->y());
    }
    // DOWN
    else if (ulaz_pozicije[id_ulaza][2] == false && popunjene_pozicije.find(std::make_pair(elementi[id_ulaza]->x(), elementi[id_ulaza]->y() + y_offset)) == popunjene_pozicije.end()) {
        ulaz_pozicije[id_ulaza][2] = true;
        ulaz_pozicije[element_id] = {true, false, false, false};
        popunjene_pozicije[std::make_pair(elementi[id_ulaza]->x(), elementi[id_ulaza]->y() + y_offset)] = true;
        return QPointF(elementi[id_ulaza]->x(), elementi[id_ulaza]->y() + y_offset);
    }
    // LEFT
    else {
        ulaz_pozicije[id_ulaza][3] = true;
        ulaz_pozicije[element_id] = {false, true, false, false};
        popunjene_pozicije[std::make_pair(elementi[id_ulaza]->x() - x_offset, elementi[id_ulaza]->y())] = true;
        return QPointF(elementi[id_ulaza]->x() - x_offset, elementi[id_ulaza]->y());
    }
}

/* export */
void MainWindow::on_actionExport_image_triggered()
{
    ui->path_label->setText(labelText["save_image"].first);
    labelText["save_image"].second = true;
    ui->path_widget->show();
}

/* enhance */
void MainWindow::on_actionEnhance_triggered()
{
    bool ok;
    unsigned id_ulaza = QInputDialog::getInt(this,"Enhance", "Input element id: ",
                                             0,0,2000,1,&ok);

    if(elementi.find(id_ulaza) == elementi.end()){
        show_unable_to_find_element_message(__FUNCTION__, id_ulaza);
        return;
    }

    if(ok){
        unsigned id = pregovarac.EnhanceImg(id_ulaza);
        // ako je enhance uspeo
        std::string display_text = "Enhance\n Element id: " + std::to_string(id);
        std::cout << display_text << std::endl;
        elementi[id] = new displayElement(QString::fromStdString(display_text), id);
        element_type[id] = "Enhance";
        QPointF new_position = find_position(id_ulaza, id);
        elementi[id]->setPos(new_position);
       // elementi[id]->moveBy(new_position.x(), new_position.y());
        scene->addItem(elementi[id]);
        scene->addItem(new Edge(elementi[id_ulaza], elementi[id]));
    }
}

/* help */
void MainWindow::on_action_help_triggered()
{
     QMessageBox::information(this,
                              tr("Help"),
                              tr("Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
                                 "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
                                 "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
                                 "aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate"
                                 " velit esse cillum dolore eu fugiat nulla pariatur."
                                 "Excepteur sint occaecat cupidatat non proident,"
                                 " sunt in culpa qui officia deserunt mollit anim id est laborum."));

}

/* about */
void MainWindow::on_action_about_triggered()
{
     QMessageBox::about(this,
                        tr("About Snap"),
                        tr("The basic idea is that the software can load photos, apply certain "
                           "transformations, display and save the result.\n\n"
                           "Snap made by:\n"
                           "\b Sanja Radulovic\n"
                           "\b Sanja Mijatovic\n"
                           "\b Nikola Novakovic\n"
                           "\b Veljko Kucinar\n"
                           "\b Milos Djuric\n"));
}

void MainWindow::show_no_elements_message(const char* str = __builtin_FUNCTION(), std::string mode = "")
{
    std::cerr << "MainWindow::" << str << "() kaze: elementi.size() is 0." << std::endl;
    if(mode == "save"){
        QMessageBox::warning(this,
                                tr("Error!"),
                                tr("No elements found!\nPlease import an image or a project before attempting to save an image or a project."));
    }
    else if(mode == "view"){
        QMessageBox::warning(this,
                                tr("Error!"),
                                tr("No elements found! Please import an image or a project."));
    }
    else if(mode == "transformacija"){
        QMessageBox::warning(this,
                                tr("Error!"),
                                tr("No elements found!\nPlease import an image or a project before applying a transformation."));
    }
    else{
        std::cerr << "Unrecognized mode: " << mode << std::endl;
        return;
    }
    return;
}

void MainWindow::show_not_found_message(const char* str = __builtin_FUNCTION(), std::string ime_fajla = "")
{
    std::string helper = "File \"" + ime_fajla + "\" not found or does not exist.";
    const char* display_message = helper.c_str();
    std::cerr << "MainWindow::" << str << "() kaze: " << helper << std::endl;
    QMessageBox::warning(this,
                            tr("Error!"),
                            tr(display_message));
}

void MainWindow::show_id_cannot_be_empty_message(const char* str = __builtin_FUNCTION())
{
    std::cerr << "MainWindow::" << str << "() kaze: id_ulaza cannot be empty." << std::endl;
    QMessageBox::warning(this,
                            tr("Error!"),
                            tr("Please enter a valid id - the field cannot be empty."));
}

void MainWindow::show_unable_to_find_element_message(const char* str = __builtin_FUNCTION(), int id = -1)
{
    std::string helper = "Unable to find element with id " + std::to_string(id) + ".\nPlease check the id and try again.";
    const char* display_message = helper.c_str();
    std::cerr << "MainWindow::" << str << "() kaze: Unable to find element with id " << std::to_string(id) << "." << std::endl;
    QMessageBox::warning(this,
                            tr("Error!"),
                            tr(display_message));
}
