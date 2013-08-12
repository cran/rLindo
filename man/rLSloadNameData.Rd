\name{rLSloadNameData}
\alias{rLSloadNameData}

\title{Load the given name data (e.g., row and column names), into a model structure.}

\description{
 R interface function for LINDO API function \code{LSloadNameData}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
rLSloadNameData(model,pszTitle = NULL,pszObjName = NULL,pszRhsName = NULL,
                pszRngName = NULL,pszBndname = NULL,paszConNames = NULL,
                paszVarNames = NULL,paszConeNames = NULL)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszTitle}{The title of the problem.}
 \item{pszObjName}{The name of the objective.}
 \item{pszRhsName}{The name of the right-hand side vector.}
 \item{pszRngName}{The name of the range vector.}
 \item{pszBndname}{The name of the bounds vector.}
 \item{paszConNames}{The constraint names.}
 \item{paszVarNames}{The variable names.}
 \item{paszConeNames}{The cone names.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
  