\name{rLSgetIUS}
\alias{rLSgetIUS}

\title{Retrieve the irreducibly unbounded set (IUS) of columns for an unbounded linear model.}

\description{
 R interface function for LINDO API function \code{LSgetIUS}. For more information,
 please refer to LINDO API User Manual.
}

\details{
   Following a call to LSfindIUS().
}

\usage{
  rLSgetIUS(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnSuf}{Number of columns in the sufficient set.}
 \item{pnIUS}{Number of columns in the IIS.}
 \item{paiVars}{An integer array containg indices of the columns in the IUS.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSfindIUS}}
}