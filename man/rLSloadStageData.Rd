\name{rLSloadStageData}
\alias{rLSloadStageData}

\title{Load stage structure for the model.}

\description{
 R interface function for LINDO API function \code{LSloadStageData}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSloadStageData(model,numStages,panRstage,panCstage)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{numStages}{Number of stages in the model.}
 \item{panRstage}{An integer array containing information about the stage membership of the constraints.}
 \item{panCstage}{An integer array containing information about the stage membership of the variables.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
