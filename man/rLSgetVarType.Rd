\name{rLSgetVarType}
\alias{rLSgetVarType}

\title{Retrieve the variable types and their respective counts in a given model.}

\description{
 R interface function for LINDO API function \code{LSgetVarType}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetVarType(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachVarTypes}{A character array containing the type of each variable.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadVarType}}
}