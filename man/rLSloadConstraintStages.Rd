\name{rLSloadConstraintStages}
\alias{rLSloadConstraintStages}

\title{Load stage structure of the constraints in the model.}

\description{
 R interface function for LINDO API function \code{LSloadConstraintStages}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSloadConstraintStages(model,panStage)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{panStage}{An integer array containing information about the stage membership of the constraints.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
