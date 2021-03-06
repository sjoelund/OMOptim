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

        @file ModItem.h
     @brief Comments for file documentation.
     @author Hubert Thieriot, hubert.thieriot@mines-paristech.fr
     Company : CEP - ARMINES (France)
     http://www-cep.ensmp.fr/english/
     @version

  */
#ifndef _ModItem_H
#define _ModItem_H

#include <QtCore/QDir>
#include <QtCore/QMutex>

#include "MOItem.h"
#include "MOVector.h"
#include "OMOptimModelica.h"
#include "ModelicaConnection.h"
#include "Variable.h"




class MOomc;

class ModItem : public MOItem
{
    Q_OBJECT

    /**
    * \brief ModItem is a class corresponding to a Modelica item (like a Model, a Component, a Block, a Record...)
    *
    * A ModItem can correspond to any modelica item. It is inherited by specific classes (like ModModel for modelica models, ModPackage for modelica packages).
    * This class provides basic structure and functions of Modelica items.
    */

    //***********************
    // Attributes
    //***********************
protected:
    bool _childrenReaden;
    MOomc* _moomc;
    QFileInfo _file;
    ModItem *_parent;
    QList<ModItem*> _children;

public :
    QMutex _readMutex;
    //***********************
    // Functions
    //***********************
public:
    ModItem(MOomc*);
    ModItem(MOomc*,ModItem* _parent,QString _name,QFileInfo filePath=QFileInfo());
    virtual QString getClassName() const {return "ModItem";};

    virtual ModItem* clone() const;
    //virtual ModItem* cloneStructure(QString newName); // clone all fields excepted connections and variables
    virtual ~ModItem(void);
    virtual Modelica::ClassRestr getClassRestr(){return Modelica::GENERIC;};

    // Data fields and management
    enum Field
    {
        NAME,
        FILEPATH
    };

    enum NameFormat
    {
        SHORT,
        WITHOUTROOT,
        FULL
    };

    static const int nbFields = 2;
    virtual unsigned getNbFields( ) const {return nbFields;};

    // General functions
    virtual QVariant getFieldValue(int iField, int role = Qt::UserRole) const;
    virtual bool setFieldValue(int iField, QVariant value);
    static QString sFieldName(int field, int role);
    virtual QString getFieldName(int i, int role = Qt::DisplayRole) const {return ModItem::sFieldName(i,role);};

    virtual QString getModClassName();
    void emitModified();

    // Parent
    ModItem* parentItem();
    void setParentItem(ModItem *);

    // Local information
    QString name(ModItem::NameFormat = ModItem::FULL);
    virtual QString filePath();

    // Tree functions
    int depth();

    //*****************************
    //Children
    //*****************************
    QList<ModItem*> children() const;
    bool addChild(ModItem*);
    void clearDescendants();
    virtual void clear();
    int compChildCount();
    int modelChildCount();
    int packageChildCount();
    int recordChildCount();
    int childCount() const;
    QStringList getChildrenNames();
    bool childrenReaden();
    void setChildrenReaden(bool);
    int indexInParent();

    bool containsItemOfClass(QString className) const;

    ModItem* child(int row) const;
    ModItem* compChild(int row) const;
    ModItem* modelChild(int row) const;
    ModItem* packageChild(int row) const;
    ModItem* recordChild(int row) const;

    ModItem* child(QString childName) const;

    //******************************
    // GUI
    //******************************
    virtual QString getStrToolTip();

public slots:
    void openMoFolder();
    void openInEditor();


signals:
    //void connectionsUpdated();
    void addedChild(ModItem*);
    void modified();
    void cleared();
};

#endif
