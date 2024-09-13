#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Центральный виджет
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Создаем кнопку для загрузки изображения
    QPushButton *loadImageButton = new QPushButton("Load Image", this);
    layout->addWidget(loadImageButton);

    // Создаем QLabel для отображения изображения
    imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    // Устанавливаем макет
    setCentralWidget(centralWidget);

    // Связываем кнопку с обработчиком
    connect(loadImageButton, &QPushButton::clicked, this, &MainWindow::on_loadImageButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadImageButton_clicked()
{
    // Открытие диалога для выбора файла изображения
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("Images (*.bmp *.jpeg *.jpg)"));

    if (!fileName.isEmpty()) {
        // Загружаем изображение в QPixmap
        QPixmap image(fileName);

        if (!image.isNull()) {
            // Отображаем изображение в QLabel
            imageLabel->setPixmap(image.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            // Если изображение не удалось загрузить
            imageLabel->setText("Failed to load image.");
        }
    }
}
