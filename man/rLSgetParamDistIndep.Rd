\name{rLSgetParamDistIndep}
\alias{rLSgetParamDistIndep}

\title{Get the stochastic data for the (independent) parametric 
       stochastic parameter at the specified event index.}

\description{
 R interface function for LINDO API function \code{LSgetParamDistIndep}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetParamDistIndep(model,iEvent)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iEvent}{Index of the discrete independent event.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{nDistType}{Distribution type of the event.}
 \item{iStage}{Stage index of the discrete-independent event.}
 \item{iRow}{Row index of the stochastic parameter.}
 \item{jCol}{Column index of the stochastic parameter.}
 \item{iStv}{Index of stochastic parameter in the instruction list.}
 \item{nParams}{Length of padParams.}
 \item{padParams}{A double array containing parameters defining the underlying distribution.}
 \item{iModifyRule}{A flag indicating whether stochastic parameters update the core model by adding or replacing.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
