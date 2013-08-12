\name{rLSoptimizeQP}
\alias{rLSoptimizeQP}

\title{Optimize a quadratic model with the best suitable solver.}

\description{
 R interface function for LINDO API function \code{LSoptimizeQP}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSoptimizeQP(model)
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

