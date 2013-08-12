\name{rLSgetRangeData}
\alias{rLSgetRangeData}

\title{Get constraint ranges.}

\description{
 R interface function for LINDO API function \code{LSgetRangeData}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSgetRangeData(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padR}{A double array containing the range data.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

