// $Id$
/**
 * This file is part of OpenModelica.
 *
 * Copyright (c) 1998-CurrentYear, Open Source Modelica Consortium (OSMC),
 * c/o Linköpings universitet, Department of Computer and Information Science,
 * SE-58183 Linköping, Sweden.
 *
 * All rights reserved.
 *
 * THIS PROGRAM IS PROVIDED UNDER THE TERMS OF GPL VERSION 3 LICENSE OR
 * THIS OSMC PUBLIC LICENSE (OSMC-PL).
 * ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS PROGRAM CONSTITUTES RECIPIENT'S ACCEPTANCE
 * OF THE OSMC PUBLIC LICENSE OR THE GPL VERSION 3, ACCORDING TO RECIPIENTS CHOICE.
 *
 * The OpenModelica software and the Open Source Modelica
 * Consortium (OSMC) Public License (OSMC-PL) are obtained
 * from OSMC, either from the above address,
 * from the URLs: http://www.ida.liu.se/projects/OpenModelica or
 * http://www.openmodelica.org, and in the OpenModelica distribution.
 * GNU version 3 is obtained from: http://www.gnu.org/copyleft/gpl.html.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without
 * even the implied warranty of  MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE, EXCEPT AS EXPRESSLY SET FORTH
 * IN THE BY RECIPIENT SELECTED SUBSIDIARY LICENSE CONDITIONS OF OSMC-PL.
 *
 * See the full OSMC Public License conditions for more details.
 *
 * Main contributor 2010, Hubert Thierot, CEP - ARMINES (France)

        @file MilpSet.h
        @brief Comments for file documentation.
        @author Hubert Thieriot, hubert.thieriot@mines-paristech.fr
        Company : CEP - ARMINES (France)
        http://www-cep.ensmp.fr/english/
        @version 0.9

  */



#ifndef MILPSET_H
#define MILPSET_H


#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include "MilpTools.h"

class MilpSet
{
public:
    MilpSet(QString name);

    virtual QString toString() = 0;

protected :
        QString _name;
};


class MilpSet0D : public MilpSet
{
public:
    MilpSet0D(QString name);

    void addItem(QString);
    void addItems(QStringList);
    void setItems(QStringList);
    QStringList items();

    virtual QString toString();

private :
    QStringList _items;
};


class MilpSet1D : public MilpSet
{
public:
    MilpSet1D(QString name);

    void addItem(QString index,QString item);
    void addItems(QString index,QStringList items);
    void setItems( QMultiMap<QString,QString>);
    QMultiMap<QString,QString> items();

    virtual QString toString();

private :
        QMultiMap<QString,QString> _items;
};



class MilpSet2D : public MilpSet
{
public:
    MilpSet2D(QString name);

    void addItem(QString indexA,QString indexB,QString item);
    void addItems(QString indexA,QString indexB,QStringList items);
    void setItems( QMultiMap<MilpKey2D,QString>);
    QMultiMap<MilpKey2D,QString> items();


    virtual QString toString();

private :
        QMultiMap<MilpKey2D,QString> _items;
};


#endif // MILPSET_H