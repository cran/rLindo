\name{rLSgetConstraintRanges}
\alias{rLSgetConstraintRanges}

\title{Retrieves the maximum allowable decrease and increase in the 
       right-hand side values of constraints for which the optimal 
       basis remains unchanged.}

\description{
 R interface function for LINDO API function \code{LSgetConstraintRanges}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSgetConstraintRanges(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padDec}{Maximum allowable decrease in the right-hand sides of constraints.}
 \item{padInc}{Maximum allowable increase in the right-hand sides of constraints.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
