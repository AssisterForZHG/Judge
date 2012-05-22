#include "FrameRequest.h"
#include "ui_FrameRequest.h"

FrameRequest::FrameRequest(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameRequest)
{
    ui->setupUi(this);
}

FrameRequest::~FrameRequest()
{
    delete ui;
}
