\name{rLSoptimize}
\alias{rLSoptimize}

\title{Optimize a continuous model by a given method.}

\description{
 R interface function for LINDO API function \code{LSoptimize}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSoptimize(model,nMethod)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nMethod}{A parameter indicating the solver to be used in optimizing the problem. Current options for this parameter are:
                  \itemize{
                      \item{LS_METHOD_FREE}
                      \item{LS_METHOD_PSIMPLEX}
                      \item{LS_METHOD_DSIMPLEX}
                      \item{LS_METHOD_BARRIER}
                      \item{LS_METHOD_NLP}
                  }
                }
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnStatus}{The status of the optimization.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
