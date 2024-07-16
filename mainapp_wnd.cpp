#include "mainapp_wnd.h"
#include "ui_mainapp_wnd.h"

mainApp_Wnd::mainApp_Wnd(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainApp_Wnd)
{
    ui->setupUi(this);

    initUI();

    init();
}

mainApp_Wnd::~mainApp_Wnd()
{
    delete ui;
    delete m_left_widegt;
    delete m_data_als_wnd;
}

void mainApp_Wnd::initUI()
{
    m_mainLayout = new QHBoxLayout;

    m_left_widegt = new main_left_widget();
    m_data_als_wnd = new data_analysis_wnd();

    m_mainLayout->addWidget(m_left_widegt);
    m_mainLayout->addWidget(m_data_als_wnd);

    this->centralWidget()->setLayout(m_mainLayout);
}

void mainApp_Wnd::init()
{

}

void mainApp_Wnd::clean()
{

}

void mainApp_Wnd::refresh_ui()
{
    data_analysis_wnd().refresh_ui();
}

bool mainApp_Wnd::set_type_name()
{

}
