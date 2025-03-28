//#ifndef EVENTHANDLER_H
//#define EVENTHANDLER_H

//#include <QMouseEvent>
//#include <QKeyEvent>
//#include <QWheelEvent>


//попробовать сделать как интерфейс изменяемый для разных ивентов

//class QuaternionEventHandler
//{
//public:
//    QuaternionEventHandler(QEvent* event):
//        _event(event){};
//    virtual ~QuaternionEventHandler() = 0;

//    virtual QQuaternion handleEvent();

//private:
//    QEvent* _event;
//};

//class TranslateEventHandler
//{
//public:
//    TranslateEventHandler(QEvent* event):
//        _event(event){};
//    virtual ~TranslateEventHandler() = 0;

//    virtual QVector3D handleEvent();

//private:
//    QEvent* _event;
//};


///////////////left mouse move

//class LeftMouseMoveEventHandler : public QuaternionEventHandler
//{
//public:
//    ~LeftMouseMoveEventHandler();

//    QQuaternion handleEvent();
//};

////////////////right mouse press

//class RightMouseMoveEventHandler : public EventHandler
//{
//public:
//    ~RightMouseMoveEventHandler();

//    QQuaternion handleEvent();
//};

////////////////left mouse press

//class LeftMousePressEventHandler : public EventHandler
//{
//public:
//    ~LeftMousePressEventHandler();

//    void handleEvent();
//};

////////////////right mouse press
//class RightMousePressEventHandler : public TranslateEventHandler
//{
//public:
//    ~RightMousePressEventHandler();

//    void handleEvent();
//};



/////////////wheel ...


//////////// key ....
/////
/////
//#endif // EVENTHANDLER_H
