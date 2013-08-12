\name{rLSloadInstruct}
\alias{rLSloadInstruct}

\title{Load instruction lists into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadInstruct}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadInstruct(model,nCons,nObjs,nVars,nNumbers,panObjSense,pszConType,
                pszVarType  = NULL,panInstruct,nInstruct,paiVars = NULL,
                padNumVal,padVarVal,paiObjBeg,panObjLen,paiConBeg,
                panConLen,padLB = NULL,padUB = NULL)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nCons}{Number of constraints in the model.}
 \item{nObjs}{Number of objectives in the model.}
 \item{nVars}{Number of variables in the model.}
 \item{nNumbers}{Number of real numbers in the model.}
 \item{panObjSense}{An integer array containing the indicator stating whether the objective is to be maximized or minimized. 
                    Valid values are \code{LS_MAX} or \code{LS_MIN}, respectively.}
 \item{pszConType}{A character array containing the type of each constraint. Each constraint is represented by a single byte 
                   in the array. Valid values for each constraint are 'L', 'E', 'G', or 'N' for 
                   less-than-or-equal-to, equal to, great-than-or-equal-to, or neutral, respectively.}
 \item{pszVarType}{A character array containing the type of each variable. Valid values for each variable are 'C', 'B', or 'I', 
                   for continuous, binary, or general integer, respectively.}
 \item{panInstruct}{An integer array containing the instruction list.}
 \item{nInstruct}{Number of items in the instruction list.}
 \item{paiVars}{An integer array containing the variable index.}
 \item{padNumVal}{A double array containing the value of each real number in the model.}
 \item{padVarVal}{A double array containing starting values for each variable in the given model.}
 \item{paiObjBeg}{An integer array containing the beginning positions on the instruction list for each objective row.}
 \item{panObjLen}{An integer array containing the length of instruction code (i.e., the number of individual instruction items) for each objective row.}
 \item{paiConBeg}{An integer array containing the beginning positions on the instruction list for each constraint row.}
 \item{panConLen}{An integer array containing the length of instruction code (i.e., the number of individual instruction items) for each constraint row.}
 \item{padLB}{A double array containing the lower bound of each variable.}
 \item{padUB}{A double array containing the upper bound of each variable.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
