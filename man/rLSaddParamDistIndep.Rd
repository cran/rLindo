\name{rLSaddParamDistIndep}
\alias{rLSaddParamDistIndep}

\title{Add a new independent stochastic parameter with a parametric distribution to the SP model.}

\description{
 R interface function for LINDO API function \code{LSaddParamDistIndep}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSaddParamDistIndep(model,iRow,jCol,iStv,nDistType,nParams,padParams,iModifyRule)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iRow}{Row index of the stochastic parameter.}
 \item{jCol}{Column index of the stochastic parameter.}
 \item{iStv}{Index of stochastic parameter in the instruction list.}
 \item{nDistType}{The parametric distribution type.}
 \item{nParams}{Length of padParams.}
 \item{padParams}{A double array containing the parameters of given distribution.}
 \item{iModifyRule}{A flag indicating whether stochastic parameters update the core model by adding or replacing.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
