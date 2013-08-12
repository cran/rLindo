\name{rLSfreeHashMemory}
\alias{rLSfreeHashMemory}

\title{Free up work arrays associated with a given model's variable name hashing.}

\description{
 R interface function for LINDO API function \code{LSfreeHashMemory}. For more information,
 please refer to LINDO API User Manual.
}

\details{
  This will release memory to the system pool, but will cause any subsequent variable name
  lookup to pause to regenerate these tables.
}

\usage{
  rLSfreeHashMemory(model)
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
