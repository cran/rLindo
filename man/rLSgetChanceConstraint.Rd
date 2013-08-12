\name{rLSgetChanceConstraint}
\alias{rLSgetChanceConstraint}

\title{Get the stochastic data for the specified chance constraint.}

\description{
 R interface function for LINDO API function \code{LSgetChanceConstraint}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetChanceConstraint(model,iChance)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iChance}{Index of the chance constraint.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{piSense}{Sense of the chance constraint.}
 \item{pnCons}{Number of constraints in the chance-constraint.}
 \item{paiCons}{An integer array containing the indices of the constraints in the constraints in the chance-constraint pnCons or more.}
 \item{pdProb}{Probability level required.}
 \item{pdObjWeight}{Weight of the chance constraint in the probabilistic objective.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
