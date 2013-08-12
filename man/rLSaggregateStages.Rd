\name{rLSaggregateStages}
\alias{rLSaggregateStages}

\title{Load stage aggregation scheme for the SP model.}

\description{
 R interface function for LINDO API function \code{LSaggregateStages}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSaggregateStages(model,panScheme,nLength)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{panScheme}{An integer array containing the stage aggregation scheme.}
 \item{nLength}{Length of panScheme.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
