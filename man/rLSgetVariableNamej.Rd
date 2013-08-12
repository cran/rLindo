\name{rLSgetVariableNamej}
\alias{rLSgetVariableNamej}

\title{Retrieve the name of a variable, given its index number.}

\description{
 R interface function for LINDO API function \code{LSgetVariableNamej}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetVariableNamej(model,iVar)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iVar}{Index of the variable whose name you wish to retrieve.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachVarName}{Name of the variable.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
