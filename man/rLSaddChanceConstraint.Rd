\name{rLSaddChanceConstraint}
\alias{rLSaddChanceConstraint}

\title{Add a new chance-constraint to the SP model.}

\description{
 R interface function for LINDO API function \code{LSaddChanceConstraint}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSaddChanceConstraint(model,iSense,nCons,paiCons,dPrLevel,dObjWeight)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iSense}{The sense of the chance-constraint. Possible values are LS_CONTYPE_LE and LS_CONTYPE_GE.}
 \item{nCons}{Number of rows in this chance constraint.}
 \item{paiCons}{An integer array containing row indices in the chanceconstraint.}
 \item{dPrLevel}{Probability level of this chance constraint.}
 \item{dObjWeight}{The constraint's weight in the probabilistic objective relative to the orignal objective function.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
