 /**
 * item_base.cpp
 * 2022-06-01 K.OHWADA
 */

#include "item_base.h"

 /**
 * constractor
 */
ItemBase::ItemBase(QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    setItemTpe(0);
    setId(0);
}


 /**
 * destractor
 */
ItemBase::~ItemBase()
{

}


 /**
 * itemType
 */
int ItemBase::itemType()
{
    return m_type;
}


 /**
 * id
 */
int ItemBase::id()
{
    return m_id;
}


 /**
 * setTpe
 */
void ItemBase::setItemTpe(int type)
{
    m_type = type;
}


 /**
 * etId
 */
void ItemBase::setId(int id)
{
    m_id = id;
}

