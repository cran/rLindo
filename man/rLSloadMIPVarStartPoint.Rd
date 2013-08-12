\name{rLSloadMIPVarStartPoint}
\alias{rLSloadMIPVarStartPoint}

\title{Provide an initial starting point for \code{LSsolveMIP}.}

\description{
 R interface function for LINDO API function \code{LSloadMIPVarStartPoint}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSloadMIPVarStartPoint(model,padPrimal)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{padPrimal}{A double array containing starting values for each variable in the given model.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

