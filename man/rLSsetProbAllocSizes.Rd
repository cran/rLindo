\name{rLSsetProbAllocSizes}
\alias{rLSsetProbAllocSizes}

\title{Increase the allocated sizes.}

\description{
 R interface function for LINDO API function \code{LSsetProbAllocSizes}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetProbAllocSizes(model,n_vars_alloc,n_cons_alloc,n_QC_alloc,n_Annz_alloc,
                       n_Qnnz_alloc,n_NLPnnz_alloc)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{n_vars_alloc}{New size for variables.}
 \item{n_cons_alloc}{New size for constraints.}
 \item{n_QC_alloc}{New size for QC terms.}
 \item{n_Annz_alloc}{New size for non-zeros.}
 \item{n_Qnnz_alloc}{New size for quadratic non-zeros.}
 \item{n_NLPnnz_alloc}{New size for NLP non-zeros.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
