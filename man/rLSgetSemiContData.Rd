\name{rLSgetSemiContData}
\alias{rLSgetSemiContData}

\title{Retrieve the semi continuous data from a model data structure.}

\description{
 R interface function for LINDO API function \code{LSgetSemiContData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetSemiContData(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{piNvars}{Number of semi-continuous variables.}
 \item{panVarndx}{An integer array containing the indices of semi-continuous variables.}
 \item{padL}{A double array containing the lower bounds of semi-continuous variables.}
 \item{padU}{A double array containing the upper bounds of semi-continuous variables.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSloadSemiContData}}
}