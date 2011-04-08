﻿// $Id$
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
 * Main contributor 2010, Hubert Thierot, CEP - ARMINES (France)

 	@file ProblemEI.cpp
 	@brief Comments for file documentation.
 	@author Hubert Thieriot, hubert.thieriot@mines-paristech.fr
 	Company : CEP - ARMINES (France)
 	http://www-cep.ensmp.fr/english/
 	@version 0.9 

  */

#include "ProblemEI.h"

ProblemEI::ProblemEI(Project* project,EIReader* eiReader,ModReader* modReader,MOomc* moomc)
{
    _type = Problem::PROBLEMEI;
    _name="EI";

    _rootEI = new EIItem();
    _eiReader = eiReader;
    _moomc = moomc;
    _project = project;
    _modReader = modReader;
}

ProblemEI::~ProblemEI(void)
{
    delete _rootEI;
}


ProblemEI::ProblemEI(const ProblemEI &problem)
:Problem(problem)
{
        if(problem._rootEI==NULL)
	{
                _rootEI=NULL;
	}
	else
                _rootEI = problem._rootEI->clone();

        _moomc = problem._moomc;
        _eiReader = problem._eiReader;
        _modReader = problem._modReader;
}

void ProblemEI::loadModel(ModModel* loadedModel)
{
    bool eraseExisting=true;
    EIItem* modelRootEI = EIModelExtractor::extractFromModClass(loadedModel,_modReader,_moomc);

    if(eraseExisting)
        unloadModel(loadedModel);

     _rootEI->addChild(modelRootEI);
}

void ProblemEI::unloadModel(ModModel* unloadedModel)
{
    int iChild= _rootEI->findChild(unloadedModel->name(),EIItem::MODEL);

    if(iChild>-1)
        _rootEI->removeChild(iChild);
}


void ProblemEI::clearInputVars()
{
        _inputVars->clear();
}

void ProblemEI::updateInputVars(MOOptVector *addedVars)
{
        if(addedVars->getUsePoints())
                _inputVars->setUsePoints(true);

        if(addedVars->getUseScan())
                _inputVars->setUseScan(true);

        _inputVars->append(*addedVars,true);

        emit inputVarsModified();
}


void ProblemEI::setInputVars(MOOptVector* variables)
{
        clearInputVars();
        updateInputVars(variables);
}

MOOptVector * ProblemEI::inputVars()
{
        return _inputVars;
}
