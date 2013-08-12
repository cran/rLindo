\name{rLSgetObjectiveRanges}
\alias{rLSgetObjectiveRanges}

\title{Retrieves the maximum allowable decrease and increase in objective 
       function coefficients for which the optimal basis remains unchanged.}

\description{
 R interface function for LINDO API function \code{LSgetObjectiveRanges}. For more information,
 please refer to LINDO API User Manual.
}


\usage{
  rLSgetObjectiveRanges(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{padDec}{Maximum allowable decrease in the objective function coefficients.}
 \item{padInc}{Maximum allowable increase in the objective function coefficients.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
