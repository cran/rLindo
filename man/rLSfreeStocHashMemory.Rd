\name{rLSfreeStocHashMemory}
\alias{rLSfreeStocHashMemory}

\title{Free up Stoch Hashtable memory used in the model for fast name lookup.}

\description{
 R interface function for LINDO API function \code{LSfreeStocHashMemory}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
  rLSfreeStocHashMemory(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
 }

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
