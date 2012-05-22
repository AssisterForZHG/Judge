#ifndef FRAMEREQUEST_H
#define FRAMEREQUEST_H

#include <QFrame>

namespace Ui {
    class FrameRequest;
}

class FrameRequest : public QFrame
{
    Q_OBJECT

public:
    explicit FrameRequest(QWidget *parent = 0);
    ~FrameRequest();

private:
    Ui::FrameRequest *ui;
};

#endif // FRAMEREQUEST_H
