\name{rLSsetPrintLogNull}
\alias{rLSsetPrintLogNull}

\title{Disable the printing log function.}

\description{
This function is R interface specific.
}

\usage{
  rLSsetPrintLogNull(model)
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

