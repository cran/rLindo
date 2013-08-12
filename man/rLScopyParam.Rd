\name{rLScopyParam}
\alias{rLScopyParam}

\title{Copy model parameters to another model.}

\description{
 R interface function for LINDO API function \code{LScopyParam}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLScopyParam(smodel,tmodel,nSolverType)
}

\arguments{
 \item{smodel}{A LINDO API model object to copy the parameters from.}
 \item{tmodel}{A LINDO API model object to copy the parameters to.}
 \item{nSolverType}{An integer specifying the solver type to copy the parameters for.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLScreateModel}}
}