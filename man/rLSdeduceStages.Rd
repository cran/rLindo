\name{rLSdeduceStages}
\alias{rLSdeduceStages}

\title{Deduce constraints and variables stage info.}

\description{
 R interface function for LINDO API function \code{LSdeduceStages}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSdeduceStages(model,nMaxStage,panRowStagesIn,panColStagesIn,panSparStage)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nMaxStage}{Maximum number of stages}
 \item{panRowStagesIn}{An integer array containing constraint stage information.}
 \item{panColStagesIn}{An integer array containing variable stage information.}
 \item{panSparStage}{An integer array containing random parameter stage information.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{panRowStagseOut}{An integer array containing constraint stage information.}
 \item{panColStagesOut}{An integer array containing variable stage information.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
