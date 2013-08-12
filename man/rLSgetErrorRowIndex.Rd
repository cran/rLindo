\name{rLSgetErrorRowIndex}
\alias{rLSgetErrorRowIndex}

\title{Retrieves the index of the row where a numeric error has occurred.}

\description{
 R interface function for LINDO API function \code{LSgetErrorRowIndex}. For more information,
 please refer to LINDO API User Manual.
}

\usage{
rLSgetErrorRowIndex(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{piRow}{The row index with numeric error.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}
