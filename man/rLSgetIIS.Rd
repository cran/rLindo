\name{rLSgetIIS}
\alias{rLSgetIIS}

\title{Retrieve the irreducibly inconsistent set (IIS) of constraints for an infeasible model.}

\description{
 R interface function for LINDO API function \code{LSgetIIS}. For more information,
 please refer to LINDO API User Manual.
}

\details{
   Following a call to LSfindIIS().
}

\usage{
  rLSgetIIS(model)
}

\arguments{
 \item{model}{A LINDO API model object, returned by \code{\link{rLScreateModel}}.}
}

\value{
 An R list object with components:
 \item{ErrorCode}{Zero if successful, nonzero otherwise.}
 \item{pnSuf_r}{Number of constraints in the sufficient set.}
 \item{pnIIS_r}{Number of rows in the IIS.}
 \item{paiCons}{An integer array containg indices of the rows in the IIS.}
 \item{pnSuf_c}{Number of column bounds in the sufficient set.}
 \item{pnIIS_c}{number of column bounds in the IIS.}
 \item{paiVars}{An integer array containg indices of the column bounds in the IIS.}
 \item{panBnds}{An integer array indicating whether the lower or the upper bound of the variable is in the IIS.}
}

\references{
 LINDO SYSTEMS home page at www.lindo.com
}

\seealso{
\code{\link{rLSfindIIS}}
}