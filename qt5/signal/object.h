/**
 * object.h
 * 2022-06-01 K.OHWADA
 */

// reference : https://www.qt.io/ja-jp/blog/2010/07/20/create-signals-and-slots

#include <QObject>


/**
 * class Object
 */
class Object : public QObject
{

    Q_OBJECT
    Q_DISABLE_COPY(Object)

public:
    explicit Object(QObject *parent = 0);
    int value() const; 
    // void setValue(int value); 


signals:
    void valueChanged(int value);

public slots:
    void setValue(int value);

private:
    int m_value;  

};
