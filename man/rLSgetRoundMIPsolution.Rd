\name{rLSgetRoundMIPsolution}
\alias{rLSgetRoundMIPsolution}

\title{Round the given MIP solution to nearest int solution.}

\description{
 R interface function for LINDO API function \code{LSgetRoundMIPsolution}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSgetRoundMIPsolution(model,padPrimal = NULL,iUseOpti)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{padPrimal}{The primal solution. If it is NULL, the solution in \code{model} will be rounded.}
 \item{iUseOpti}{Whether to use reoptimization after integers have been rounded and fixed to there optimal value.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padPrimalRound}{The rounded solution.}
 \item{pdObjRound}{Objective value of the rounded solution.}
 \item{pdPfeasRound}{Infeasibility of the rounded solution.}
 \item{pnstatus}{Status of solution if reoptimization have been used.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

