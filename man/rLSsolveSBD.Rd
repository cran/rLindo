\name{rLSsolveSBD}
\alias{rLSsolveSBD}

\title{Optimize a given LP or MILP model with Benders' decomposition.}

\description{
 R interface function for LINDO API function \code{LSsolveSBD}. For more information,
 please refer to LINDO API User Manual.
}

\details{
 The model should have dual angular block structure to be solved with this routine. 
 The dual angular structure is specified explicitly with the argument list.
}

\usage{
  rLSsolveSBD(model,nStages,panRowStage,panColStage)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nStages}{Number of stages/blocks in the dual angular model.}
 \item{panRowStage}{The stage indices of constraints. Stage-0 indicates linking row or column.}
 \item{panColStage}{The stage indices of variables. Stage-0 indicates linking row or column.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnStatus}{The status of the optimization.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

