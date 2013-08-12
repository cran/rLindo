\name{rLSsolveGOP}
\alias{rLSsolveGOP}

\title{Optimize a global optimization problem.}

\description{
 R interface function for LINDO API function \code{LSsolveGOP}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSsolveGOP(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnStatus}{The status of the optimization.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
