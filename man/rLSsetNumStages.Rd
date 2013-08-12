\name{rLSsetNumStages}
\alias{rLSsetNumStages}

\title{Set number of stages in the model.}

\description{
 R interface function for LINDO API function \code{LSsetNumStages}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetNumStages(model,numStages)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{numStages}{Number of stages in the model.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
