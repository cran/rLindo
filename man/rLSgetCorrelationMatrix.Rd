\name{rLSgetCorrelationMatrix}
\alias{rLSgetCorrelationMatrix}

\title{Get the correlation structure between variables.}

\description{
 R interface function for LINDO API function \code{LSgetCorrelationMatrix}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSgetCorrelationMatrix(model,iFlag,nCorrType)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{iFlag}{An integer specifying the sample (original or corr-induced). Possible values are:
                \itemize{
                   \item{0:} {Use independent sample}
                   \item{1:} {Use dependent (correlation induced) sample} 
                }
             }
 \item{nCorrType}{Correlation type. Possible values are:
                     \itemize{   
                        \item{LS_CORR_PEARSON}
                        \item{LS_CORR_SPEARMAN}
                        \item{LS_CORR_KENDALL}
                        \item{LS_CORR_TARGET}
                     }
                  }
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnQCnnz}{Number of nonzero correlation coefficients.}
 \item{paiQCcols1}{An integer array containing the first index of variable the correlation term belongs to.}
 \item{paiQCcols2}{An integer array containing the second index of variable the correlation term belongs to.}
 \item{padQCcoef}{A double array containing the correlation terms.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
