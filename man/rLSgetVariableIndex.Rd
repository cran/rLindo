\name{rLSgetVariableIndex}
\alias{rLSgetVariableIndex}

\title{Retrieve the index of a variable, given its name.}

\description{
 R interface function for LINDO API function \code{LSgetVariableIndex}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetVariableIndex(model,pszVarName)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{pszVarName}{Name of the variable whose index you wish to retrieve.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{piVar}{Index of the variable.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSgetVariableNamej}}
}