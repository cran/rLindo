\name{rLSloadCorrelationMatrix}
\alias{rLSloadCorrelationMatrix}

\title{Load a correlation matrix to be used by the sampling scheme in stochastic programming.}

\description{
 R interface function for LINDO API function \code{LSloadCorrelationMatrix}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSloadCorrelationMatrix(model,nDim,nCorrType,nQCnnz,paiQCcols1,
                           paiQCcols2,padQCcoef)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{nDim}{Number of stochastic parameters involved in the correlation structure.}
 \item{nCorrType}{Correlation type. Possible values are:
                     \itemize{   
                        \item{LS_CORR_PEARSON}
                        \item{LS_CORR_SPEARMAN}
                        \item{LS_CORR_KENDALL}
                     }
                  }
 \item{nQCnnz}{Number of nonzero correlation coefficients.}
 \item{paiQCcols1}{An integer array containing the first index of variable the correlation term belongs to.}
 \item{paiQCcols2}{An integer array containing the second index of variable the correlation term belongs to.}
 \item{padQCcoef}{A double array containing the correlation terms.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
