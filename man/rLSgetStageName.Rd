\name{rLSgetStageName}
\alias{rLSgetStageName}

\title{Get scenario name by index.}

\description{
 R interface function for LINDO API function \code{LSgetStageName}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetStageName(model,nIndex)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nIndex}{Index of the Stage.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pachName}{Name of the Stage.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
