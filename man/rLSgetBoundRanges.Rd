\name{rLSgetBoundRanges}
\alias{rLSgetBoundRanges}

\title{Retrieves the maximum allowable decrease and increase in the
       primal variables for which the optimal basis remains unchanged.}

\description{
 R interface function for LINDO API function \code{LSgetBoundRanges}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSgetBoundRanges(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padDec}{Maximum allowable decrease in the lower and upper bounds.}
 \item{padInc}{Maximum allowable increase in the lower and upper bounds.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
