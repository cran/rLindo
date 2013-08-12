\name{rLScalinfeasMIPsolution}
\alias{rLScalinfeasMIPsolution}

\title{Calculate the feasibility of a MIP solution.}

\description{
 R interface function for LINDO API function \code{LScalinfeasMIPsolution}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLScalinfeasMIPsolution(model,padPrimalMipsol = NULL)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{padPrimalMipsol}{The primal solution. If it is NULL, the procedure returns the infeasibility of the internal solution if any.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pdIntPfeas}{Infeasibility of int variables.}
 \item{pbConsPfeas}{Infeasibility of constraints.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

