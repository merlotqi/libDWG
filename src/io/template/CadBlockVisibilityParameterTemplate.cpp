/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#include <dwg/io/template/CadBlockVisibilityParameterTemplate_p.h>

namespace dwg {

/* --------------------- CadEvaluationExpressionTemplate -------------------- */
CadEvaluationExpressionTemplate::CadEvaluationExpressionTemplate(EvaluationExpression *object)
    : CadTemplateT<EvaluationExpression *>(object)
{
}

CadEvaluationExpressionTemplate::~CadEvaluationExpressionTemplate() {}


/* ------------------------- CadBlockElementTemplate ------------------------ */
CadBlockElementTemplate::CadBlockElementTemplate(BlockElement *object) : CadEvaluationExpressionTemplate(object) {}

BlockElement *CadBlockElementTemplate::blockElement() const
{
    return nullptr;
}


/* ------------------------ CadBlockParameterTemplate ----------------------- */
CadBlockParameterTemplate::CadBlockParameterTemplate(BlockParameter *object) : CadBlockElementTemplate(object) {}

BlockParameter *CadBlockParameterTemplate::blockParameter() const
{
    return nullptr;
}


/* ---------------------- CadBlock1PtParameterTemplate ---------------------- */
CadBlock1PtParameterTemplate::CadBlock1PtParameterTemplate(Block1PtParameter *object)
    : CadBlockParameterTemplate(object)
{
}

Block1PtParameter *CadBlock1PtParameterTemplate::block1PtParameter() const
{
    return nullptr;
}

}// namespace dwg
