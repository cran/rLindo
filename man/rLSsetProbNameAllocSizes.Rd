\name{rLSsetProbNameAllocSizes}
\alias{rLSsetProbNameAllocSizes}

\title{Increase the allocated sizes for how much space is needed for storing names.}

\description{
 R interface function for LINDO API function \code{LSsetProbNameAllocSizes}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSsetProbNameAllocSizes(model,n_varname_alloc,n_rowname_alloc)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 \item{n_varname_alloc}{New size for variable names.}
 \item{n_rowname_alloc}{New size for constraint names.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
